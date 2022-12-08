#pragma once

#include <cstdio>
#include <algorithm>
#include "array_bundle.h"

namespace bmstu {
    template<typename Type>
    class vector {
    public:
        struct iterator {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Type;
            using pointer = Type *;
            using reference = Type &;

            iterator(pointer ptr) : m_ptr(ptr) {}

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

            }

            iterator &operator+(size_t n) noexcept {/*code*/}

            iterator &operator-(size_t n) noexcept {/*code*/}

        private:
            pointer m_ptr;
        };


        using const_iterator = const iterator;

        vector() noexcept = default;

        vector(size_t size, const Type &value = Type{}) : size_(size), capacity_(size), data_(size) {
            auto first = begin();
            auto last = end();
            for (; first != last; ++first) {
                *first = value;
            }
        }

        vector(const vector<Type> &other) {/*code*/}

        vector(vector<Type> &&other) {/*code*/}

        vector(std::initializer_list<Type> ilist) {
            data_[ilist.size()] = 0;
            size_ = ilist.size();
            for (int i = 0; i < ilist.size(); i++) {
                data_[i] = *(data_.begin() + i);
            }
            data_[size_] = '\0';
        }

        void clear() noexcept {
            if (data_ = nullptr) {
                delete[] data_;
                data_ = nullptr;
            }
            size_ = 0;
        }

        vector &operator=(const vector<Type> &other) {
            if (this != other) {
                if (other.empty()) {
                    clear();
                } else {
                    auto copy(std::move(other));
                    this->swap(copy);
                }
            }
            return this;
        }

        vector &operator=(vector<Type> &&other) {/*code*/
        }

        iterator begin() noexcept {
            return data_.Get();
        }

        iterator end() noexcept {
            return data_.Get() + size_;
        }

        const_iterator begin() const noexcept {
            return data_.Get();
        }

        const_iterator end() const noexcept {
            return data_.Get() + size_;
        }

        const_iterator cbegin() const noexcept {
            return data_.Get();
        }

        const_iterator cend() const noexcept {
            return data_.Get() + size_;
        }

        typename iterator::reference operator[](size_t index) noexcept {
            return data_[index];
        }

        typename const_iterator::reference operator[](size_t index) const noexcept {
            return data_[index];
        }

        typename iterator::reference at(size_t index) {

        }

        typename const_iterator::reference at(size_t index) const {/*code*/}

        size_t size() const noexcept {
            return size_;
        }

        size_t capacity() const noexcept {
            return capacity_;
        }

        bool empty() const noexcept {
            if (size_ == 0) {
                return true;
            } else {
                return false;
            }
        }

        void swap(vector &other) noexcept {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            data_.swap(other.data_);
        }

        friend void swap(vector<Type> &lhs, vector<Type> &rhs) {
            lhs.swap(rhs);
        }

        void resize(size_t new_size) {
            data_ = new Type[new_size];
            size_ = new_size;
        }

        void reserve(size_t new_capacity) {

        }

        iterator insert(const_iterator pos, Type &&value) {

        }

        iterator insert(const_iterator pos, const Type &value) {

        }

        void push_back(const Type &value) {

        }

        void push_back(Type &&value) {

        }

        void pop_back() noexcept {

        }

        friend bool operator==(const vector<Type> &l, const vector<Type> &r) {

        }

        friend bool operator!=(const vector<Type> &l, const vector<Type> &r) {

        }

        friend bool operator<(const vector<Type> &l, const vector<Type> &r) {

        }

        friend bool operator>(const vector<Type> &l, const vector<Type> &r) {

        }

        friend bool operator<=(const vector<Type> &l, const vector<Type> &r) {

        }

        friend bool operator>=(const vector<Type> &l, const vector<Type> &r) {

        }

        friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other) {

        }

    private:
        static bool lexicographical_compare_(const vector<Type> &l, const vector<Type> &r) {

        }

        size_t size_ = 0;
        size_t capacity_ = 0;
        array_bundle<Type> data_;
    };
}