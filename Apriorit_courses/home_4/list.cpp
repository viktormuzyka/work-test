#include <iostream>
#include <ctime>
#include <memory>
#include <forward_list>

template <typename T>
struct Node {
	T data;
	std::unique_ptr<Node<T>> next;
	Node(T data) : data{ data }, next{ nullptr } {}
	~Node() {
		//std::cout << "Destroy node with data: " << data << '\n';
	}
};
template <typename T>
struct List {
	List() : head{ nullptr } {};

	void push(T data) {
		auto temp{ std::make_unique<Node<T>>(data) };
		if (head) {
			temp->next = std::move(head);
			head = std::move(temp);

		}
		else {
			head = std::move(temp);
		}
	}
	int get_size() {
		int size=0;
		Node<T>* head = this->head.get();
		while (head) {
			head = head->next.get();
			size++;
		}
		return size;
	}
	void delete_item(T data_to_remove) {
		Node<T>* head = this->head.get();
		Node<T>* before_head = this->head.get();
		bool first_step = 1;
		while (head) {
			//std::cout << head->data << " != " << data_to_remove << std::endl;
			if (head->data == data_to_remove) {
				if (first_step) {
					this->head = std::move(head->next);
					return;
				}
				else {
					before_head->next = std::move(head->next);
					head = nullptr;
					return;
				}
			}
			before_head = head;
			head = head->next.get();
			first_step = 0;

		}
		return;
	}
	void print() {
		Node<T>* head = this->head.get();
		while (head) {
			std::cout << head->data << " ";
			head = head->next.get();
		}
		std::cout << std::endl;
	}
	void clean() {
		while (head) {
			head = std::move(head->next);
		}
	}
	List(const List& list) {
		Node<T>* root = list.head.get();

		std::unique_ptr<Node<T>> new_head{ nullptr };
		Node<T>* pnew_head{ nullptr };
		while (root) {
			auto temp{ std::make_unique<Node<T>>(root->data) };
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
		Node<T>* root = head.get();
		while (root) {
			tmp.push(root->data);
			root = root->next.get();
		}
		clean();
		head = std::move(tmp.head);
	}

private:
	std::unique_ptr<Node<T>> head;
};


int main() {
	List<int> list;

     for (int i = 0; i < 10; ++i) {
         list.push(i);
	}
	 list.push(5);
	 list.print();
	 list.delete_item(5);
	 list.delete_item(8);
	 list.print();

     list.clean();
	 list.print();

     list.push(-1);
     list.push(-2);
     list.push(-3);
     list.push(-4);
     list.push(-5);
	 list.print();

	 List<int> list2 = list;
	 list2.print();

	 List<int> list3 = std::move(list);
	 list.print();
	 list3.print();

     list3.reverse();
	 list3.print();
	 std::cout << list3.get_size() << std::endl;
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

	std::cout << "Forward list" << std::endl;
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

