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
        bool ret = (from[pos] >= 0 and from[pos] <= m_s and to[from[pos]] == pos);
        return ret;
    }

   public:
    InitializableArray(size_t size, const T &defaultValue) : m_s(0), m_defaultValue(defaultValue) {
        values.reserve(size);
        from.reserve(size);
        to.reserve(size);
    }

    const T &operator[](size_t pos) const {
        if (isWritten(pos)) {
            return values[pos];
        }
        return m_defaultValue;
    }

    void insert(size_t pos, const T &value) {
        values.insert(values.begin() + pos, value);
        from.insert(from.begin() + pos, m_s);
        to.insert(to.begin() + m_s, pos);
        ++m_s;
    }

    size_t size() const { return values.capacity(); }

   private:
    size_t              m_s;
    T                   m_defaultValue;
    std::vector<T>      values;
    std::vector<size_t> from;
    std::vector<size_t> to;
};

} // namespace arr