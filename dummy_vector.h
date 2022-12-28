#pragma once

#include <iostream>
#include "array_bundle.h"

namespace bmstu {
    template<typename Type>
    class dummy_vector {
    public:
        /// только заметил, что мы ошиблись)
        /// const_iterator -> это объект где конст pointer
        struct const_iterator;

        struct iterator {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Type;
            using pointer = Type *;
            using reference = Type &;

            iterator(pointer ptr) : m_ptr(ptr) {}

            operator const_iterator() {
                return const_iterator(m_ptr);
            }

            reference operator*() const {
                return *m_ptr;
            }

            pointer operator->() {
                return m_ptr;
            }

            iterator &operator++() {
                ++m_ptr;
                return *this;
            }

            iterator &operator--() {
                --m_ptr;
                return *this;
            }

            iterator &operator=(const iterator &other) {
                this->m_ptr = other.m_ptr;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator operator--(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const iterator &a, const iterator &b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const iterator &a, const iterator &b) {
                return !(a == b);
            }

            friend ptrdiff_t operator-(const iterator &a, const iterator &b) {
                return a.m_ptr - b.m_ptr;
            }

            iterator &operator+(size_t n) noexcept {
                m_ptr = m_ptr + n;
                return *this;
            }

            iterator &operator-(size_t n) noexcept {
                m_ptr = m_ptr - n;
                return *this;
            }

        private:
            pointer m_ptr;
        };

        /// константный итератор это итератор который
        /// значение типа константное и ссылка константная
        /// мы можем перемещаться по памяти .. но вот изменить объект не сможем
        struct const_iterator {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = const Type;
            using pointer = Type *;
            using reference = const Type &;

            const_iterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const {
                return *m_ptr;
            }

            pointer operator->() {
                return m_ptr;
            }

            const_iterator &operator++() {
                ++m_ptr;
                return *this;
            }

            const_iterator &operator--() {
                --m_ptr;
                return *this;
            }

            const_iterator &operator=(const iterator &other) {
                this->m_ptr = other.m_ptr;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            const_iterator operator--(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const const_iterator &a, const const_iterator &b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const const_iterator &a, const const_iterator &b) {
                return !(a == b);
            }

            friend ptrdiff_t operator-(const const_iterator &a, const const_iterator &b) {
                return a.m_ptr - b.m_ptr;
            }

            const_iterator &operator+(size_t n) noexcept {
                m_ptr = m_ptr + n;
                return *this;
            }

            const_iterator &operator-(size_t n) noexcept {
                m_ptr = m_ptr - n;
                return *this;
            }

        private:
            pointer m_ptr;
        };

        dummy_vector() noexcept = default;

        dummy_vector(size_t size, const Type &value = Type{}) :
                size_(size), capacity_(size), data_(size) {
            auto first = begin();
            auto last = end();
            for (; first != last; ++first) {
                *first = value;
            }
        }

        //Конструктор копироания
        dummy_vector(const dummy_vector<Type> &other) : size_(other.size()), capacity_(other.capacity()), data_(size_) {
            std::copy(other.begin(), other.end(), begin());
        }

        //Конструктор перемещения
        dummy_vector(dummy_vector<Type> &&other) {
            this->swap(other);
        }

        dummy_vector(std::initializer_list<Type> ilist) : size_(ilist.size()), capacity_(ilist.size()),
                                                          data_(ilist.size()) {
            std::copy(ilist.begin(), ilist.end(), begin());
        }

        void Clear() noexcept {
            size_ = 0;
        }

        //Оперотор копирующего присваивания
        dummy_vector &operator=(const dummy_vector<Type> &other) {
            /// самоприсваивание
            if (this != &other) {
                if (other.empty()) {
                    Clear();
                } else {
                    auto copy(other);
                    this->swap(copy);
                }
            }
            return *this;
        }

        //Оперотор перемещающего присваивания
        dummy_vector &operator=(const dummy_vector<Type> &&other) {
            /// самоприсваивание
            if (this != &other) {
                if (other.empty()) {
                    Clear();
                } else {
                    auto copy(std::move(other));
                    this->swap(copy);
                }
            }
            return *this;
        }

        friend dummy_vector<Type> operator+(const dummy_vector<Type> & left, const dummy_vector<Type> & right){
            size_t size = left.size_ + right.size_;
            dummy_vector<Type> result(size);
            std::copy(left.begin(), left.end(), result.begin());
            std::copy(right.begin(), right.end(), result.begin() + left.size_) + 1;
            return result;
        }

        dummy_vector<Type> operator+=(const dummy_vector<Type> & other) {
            size_t new_size = size_ + other.size_;
            dummy_vector<Type> copy(*this);
            dummy_vector<Type> result(new_size);
            result = copy + other;
            *this = (std::move(result));
            return *this;
        }

        ///Iterators
        iterator begin() noexcept {
            return iterator(data_.Get());
        }

        iterator end() noexcept {
            return iterator(data_.Get() + size_);
        }

        const_iterator begin() const noexcept {
            return const_iterator(data_.Get());
        }

        const_iterator end() const noexcept {
            return const_iterator(data_.Get() + size_);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(data_.Get());
        }

        const_iterator cend() const noexcept {
            return const_iterator(data_.Get() + size_);
        }

        typename iterator::reference operator[](size_t index) noexcept {
            return data_[index];
        }

        typename const_iterator::reference operator[](size_t index) const noexcept {
            return const_cast <typename const_iterator::reference> (data_[index]);
        }

        typename iterator::reference at(size_t index) {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return data_[index];
            }
        }

        typename const_iterator::reference at(size_t index) const {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return const_cast <typename const_iterator::value_type>(data_[index]);
            }

        }

        //getters
        size_t size() const noexcept {
            return size_;
        }

        size_t capacity() const noexcept {
            return capacity_;
        }

        bool empty() const noexcept {
            return (size_ == 0);
        }

        void swap(dummy_vector &other) noexcept {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            data_.swap(other.data_);
        }

        friend void swap(dummy_vector<Type> &lhs, dummy_vector<Type> &rhs) {
            lhs.swap(rhs);
        }

        void resize(size_t new_size) {
            if (new_size > capacity_) {
                size_t new_capacity = std::max(new_size, capacity_ * 2);
                reserve(new_capacity);
                size_ = new_size;


            } else if (new_size < size_) {
                std::fill(begin() + new_size, end(), Type{});
                size_ = new_size;
            }
            std::fill(end(), begin() + new_size, Type{});

            size_ = new_size;

        }


        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                array_bundle<Type> tmp(new_capacity);
                std::move(data_.Get(), data_.Get() + size_, tmp.Get());
                data_.swap(tmp);
                capacity_ = new_capacity;
            }

        }

        iterator insert(const_iterator pos, Type &&value) {
            size_t n = pos - begin();
            if (capacity_ == 0) {
                reserve(1);
            }
            if (size_ == capacity_) {
                capacity_ *= 2;
            }
            array_bundle<Type> temp(capacity_);
            std::move(begin(), begin() + n, temp.Get());
            std::move_backward(begin() + n, begin() + size_, temp.Get() + size_ + 1);
            temp.Get()[n] = std::move(value);
            data_.swap(temp);
            size_++;
            return begin() + n;
        }

        iterator insert(const_iterator pos, const Type &value) {
            Type copy = value;
            return insert(pos, std::move(copy));
        }

        void push_back(const Type &value) {
            Type tmp = value;
            push_back(tmp);
        }

        void push_back(Type &&value) {
            insert(end(), std::move(value));
        }

        void pop_back() noexcept {
            if (!empty()) {
                --size_;
            }
        }

        friend bool operator==(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            if (l.size_ == r.size_) {
                for (auto fl = l.begin(), fr = r.begin(); fl != l.end(); ++fl, ++fr) {
                    if (*fl != *fr) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        friend bool operator!=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return !(l == r);
        }

        friend bool operator<(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return lexicographical_compare_(l, r);
        }

        friend bool operator>(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return (r < l);
        }

        friend bool operator<=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return !(r < l);
        }

        friend bool operator>=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return !(l < r);
        }

        friend std::ostream &operator<<(std::ostream &os, const dummy_vector<Type> &other) {
            os << "[";
            for (int i = 0; i < other.size_ - 1; ++i) {
                os << other[i] << ", ";
            }
            os << other[other.size_ - 1];
            os << "]";
            return os;
        }

    private:
        static bool lexicographical_compare_(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            auto lf = l.begin(), rf = r.begin();
            for (; (lf != l.end()) && (rf != r.end()); ++lf, ++rf) {
                if (*lf < *rf) {
                    return true;
                }
                if (*rf < *lf) {
                    return false;
                }
            }
            return (rf != r.end()) && (lf == l.end());
        }

        size_t size_ = 0;
        size_t capacity_ = 0;
        array_bundle<Type> data_;
    };
}