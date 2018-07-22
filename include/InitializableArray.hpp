#pragma once

#include <vector>

namespace arr {

template <typename T>
class InitializableArray {
   private:
    bool isWritten(size_t pos) const {
        if (m_s == 0) {
            return false;
        }
        bool ret = (m_from[pos] >= 0 and m_from[pos] <= m_s and m_to[m_from[pos]] == pos);
        return ret;
    }

   public:
    InitializableArray(size_t size, const T &defaultValue) : m_s(0), m_defaultValue(defaultValue) {
        m_values.reserve(size);
        m_from.reserve(size);
        m_to.reserve(size);
    }

    InitializableArray(const InitializableArray &other)
        : m_s(other.ms),
          m_defaultValue(other.m_defaultValue),
          m_values{other.m_values},
          m_from(other.m_from),
          m_to(other.m_to) {}

    InitializableArray &operator=(const InitializableArray &other) {
        std::swap(m_s, other.m_s);
        std::swap(m_defaultValue, other.m_defaultValue);
        std::swap(m_values, other.m_values);
        std::swap(m_from, other.m_from);
        std::swap(m_to, other.m_to);
        return *this;
    }

    inline const T &operator[](size_t pos) const {
        if (!isWritten(pos)) {
            return m_defaultValue;
        }
        return m_values[pos];
    }

    inline void insert(size_t pos, const T &value) {
        m_values[pos] = value;
        m_from[pos] = m_s;
        m_to[pos] = pos;
        ++m_s;
    }

    inline size_t size() const { return m_values.capacity(); }

    inline void clear() { m_s = 0; }

    inline void clear(size_t pos) {
        if(isWritten(pos)){
            m_to[m_from[pos]] = m_to[m_s];
            m_from[m_to[m_s]] = m_from[pos];
            --m_s;
        }
    }

    class iterator {
       public:
        using iterator_category = typename std::vector<T>::iterator::iterator_category;
        using value_type = typename std::vector<T>::iterator::value_type;
        using difference_type = typename std::vector<T>::iterator::difference_type;
        using pointer = typename std::vector<T>::iterator::pointer;
        using reference = typename std::vector<T>::iterator::reference;


        iterator(const InitializableArray<T> &initializableArray, size_t pos)
            : m_initializableArray(initializableArray), m_pos(pos) {}

        iterator &operator++() {
            ++m_pos;
            return *this;
        }

        difference_type operator-(iterator &other) {
            return m_pos - other.m_pos;
        }

        const T &operator*() { return m_initializableArray[m_pos]; }

        bool operator!=(iterator &other) const {
            return m_pos != other.m_pos;// and m_initializableArray != other.m_initializableArray;
        }

       private:
        const InitializableArray<T> &m_initializableArray;
        size_t                       m_pos;
    };

    // iterator begin();
    // iterator end();

    iterator begin() { return iterator(*this, 0); }
    iterator end() { return iterator(*this, m_values.capacity()); }

   private:
    size_t              m_s;
    const T             m_defaultValue;
    std::vector<T>      m_values;
    std::vector<size_t> m_from;
    std::vector<size_t> m_to;
};

} // namespace arr