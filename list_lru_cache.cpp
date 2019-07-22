class LRUCache {
public:
	LRUCache(int capacity) {
		cap = capacity;
	}

	int get(int key) {
		auto it = vp.find(key);
		if (it != vp.end()) {
			recencies.splice(recencies.end(), recencies, it->second->recency_pos);
			return it->second->val;
		}
		return -1;
	}

	void put(int key, int value) {
		auto it_vp = vp.find(key);
		if (it_vp != vp.end()) {
			it_vp->second->val = value;
			recencies.splice(recencies.end(), recencies, it_vp->second->recency_pos);
			return;
		}

		// reach here when key is not present
		if (vp.size() == cap) {
			vp.erase(recencies.front());
			auto p = vp.emplace(key, new node(value, recencies.begin()));
			recencies.front() = p.first;
			recencies.splice(recencies.end(), recencies, recencies.begin());
		}
		else {
			// vp size has not reached cap
			auto p = vp.emplace(key, new node(value, recencies.end()));
			recencies.push_back(p.first);
			--(p.first->second->recency_pos);
		}
	}

private:
	struct node {
		node(int v, list<unordered_map<int, unique_ptr<node>>::iterator>::iterator it) : val(v), recency_pos(it) {
		}

		int val;
		list<unordered_map<int, unique_ptr<node>>::iterator>::iterator recency_pos;
	};

	list<unordered_map<int, unique_ptr<node>>::iterator> recencies;

	unordered_map<int, unique_ptr<node>> vp;

	int cap;

	void printRecencies() {
		for (const auto &it_vp : recencies) {
			cout << "key: " << it_vp->first;

			auto it_rec = it_vp->second->recency_pos;
			if (it_rec != recencies.end()) {
				cout << "key: " << (*it_rec)->first;
			}
			else {
				cout << "end() iterator";
			}
		}
		cout << endl;
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
