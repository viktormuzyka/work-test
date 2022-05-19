#include <iostream>
#include <ctime>
#include <memory>
#include <forward_list>

struct Node {
	int data;
	std::unique_ptr<Node> next;
	Node(int data) : data{ data }, next{ nullptr } {}
	~Node() {
		//std::cout << "Destroy node with data: " << data << '\n';
	}
};
struct List {
	List() : head{ nullptr } {};

	void push(int data) {
		auto temp{ std::make_unique<Node>(data) };
		if (head) {
			temp->next = std::move(head);
			head = std::move(temp);

		}
		else {
			head = std::move(temp);
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const List& list);
	void clean() {
		while (head) {
			head = std::move(head->next);
		}
	}
	List(const List& list) {
		Node* root = list.head.get();

		std::unique_ptr<Node> new_head{ nullptr };
		Node* pnew_head{ nullptr };
		while (root) {
			auto temp{ std::make_unique<Node>(root->data) };
			if (new_head == nullptr) {
				new_head = std::move(temp);
				pnew_head = new_head.get();
			}
			else {
				pnew_head->next = std::move(temp);
				pnew_head = pnew_head->next.get();
			}
			root = root->next.get();
		}
		head = std::move(new_head);
	}


	List(List&& list) {
		head = std::move(list.head);
	}
	~List() {
		clean();
	}
	void pop() {
		if (head == nullptr) {
			return;
		}

		std::unique_ptr<Node> temp = std::move(head);
		head = std::move(temp->next);
	}
	void reverse() {
		List tmp;
		Node* root = head.get();
		while (root) {
			tmp.push(root->data);
			root = root->next.get();
		}
		clean();
		head = std::move(tmp.head);
	}

private:
	std::unique_ptr<Node> head;
};
std::ostream& operator<<(std::ostream& os, const List& list) {
	Node* head = list.head.get();
	while (head) {
		os << head->data << ' ';
		head = head->next.get();
	}
	return os;
}

int main() {
	List list;

     for (int i = 0; i < 10; ++i) {
         list.push(i);

	}
     std::cout << list << '\n';

     list.clean();
     std::cout << list << '\n';

     list.push(-1);
     list.push(-2);
     list.push(-3);
     list.push(-4);
     list.push(-5);
     std::cout << list << '\n';

     List list2 = list;
     std::cout << list2 << '\n';

     List list3 = std::move(list);
     std::cout << list << '\n';
    std::cout << list3 << '\n';

     list3.reverse();
     std::cout << list3 << '\n';
	/*
	*speed test
	*/
	/*unsigned int start = 0, end = 0, search = 0;
	std::cout << "List" << std::endl;
	start = clock();
	List list;
	for (int i = 0; i < 10000000; ++i) {
		list.push(i);
	}
	list.clean();
	end = clock();
	search += end - start;
	std::cout << "	Push 10mln elements: " << search << " ms" << std::endl;

	std::cout << "Stoward list" << std::endl;
	start = clock();
	std::forward_list<int> f_list;
	for (int i = 0; i < 10000000; ++i) {
		f_list.emplace_front(i);
	}
	f_list.clear();
	end = clock();
	search += end - start;
	std::cout << "	Push 10mln elements: " << search << " ms" << std::endl;*/
}

