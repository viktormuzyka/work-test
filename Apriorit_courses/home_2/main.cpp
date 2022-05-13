#ifndef CODEREVIEWTASK_MYVECTOR_HPP
#define CODEREVIEWTASK_MYVECTOR_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 *    1) begin(), cbegin(), end(), cend()
 *    2) empty(), size()
 *    3) reserve(), clear()
 */

template <typename T>
class MyVector {
		typedef std::pair<std::vector<T>, std::vector<std::string>> VectorsPair;
	public:
		MyVector() : m_names(std::make_shared<VectorsPair>(VectorsPair())) {}

		MyVector(const MyVector& other) : m_names(other.m_names) {}

		void push_back(const T& obj, const std::string& name) {
			copy_data();
			m_names->first.push_back(obj);
			m_names->second.push_back(name);
			//(*m_ref_ptr)++;???
		}

		std::pair<const T&, const std::string&> operator[](int index) const {
			if (index >= size()) {
				throw std::out_of_range("index out of range");
			}
			return {m_names->first[index], m_names->second[index]};
		}
		//code repetition or const_cast?
		std::pair<T&, std::string&> operator[](int index) {
			copy_data();

			if (index >= size()) {
				throw std::out_of_range("index out of range");
			}
			return {m_names->first[index], m_names->second[index]};
		}

		const T& operator[](const std::string& name) const {
			auto iter = std::find(m_names->second.begin(), m_names->second.end(), name);
			if (iter == m_names->second.end()) {
				throw std::invalid_argument(name + " is not found in the MyVector");
			}
			return m_names->first[iter - m_names->second.begin()];
		}

		T& operator[](const std::string& name) {
			copy_data();
			auto iter = std::find(m_names->second.begin(), m_names->second.end(), name);
			if (iter == m_names->second.end()) {
				throw std::invalid_argument(name + " is not found in the MyVector");
			}
			return m_names->first[iter - m_names->second.begin()];
		}
		/*
		*task 6
		*/
		auto cbegin() const {
			return m_names->first.cbegin();
		}
		auto cend() const {
			return m_names->first.cend();
		}
		auto begin() const {
			return cbegin();
		}
		auto end() const {
			return cend();
		}
		auto begin() {
			copy_data();
			return m_names->first.begin();
		}
		auto end() {
			copy_data();
			return m_names->first.end();
		}
		void clear() {
			//m_names nullptr
			m_names = std::make_shared<VectorsPair>(VectorsPair());
		}
		bool empty() const {
			return m_names->first.empty();
		}
		std::size_t size() const {
			return m_names->first.size();
		}
		void reserve(std::size_t size) const {
			m_names->reserve(size);
		}
	private:
		void copy_data() {
			auto temp = m_names.get();
			if(!(temp == nullptr || m_names.unique())) {
				m_names = std::make_shared<VectorsPair>(VectorsPair(*temp));
			}
		}
		// Use copy-on-write idiom for efficiency (not a premature optimization)
		std::shared_ptr<VectorsPair> m_names;
};


#endif
