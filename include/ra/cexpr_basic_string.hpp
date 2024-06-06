#include <stdexcept>

namespace ra::cexpr {

// A basic string class template for use in constexpr contexts.
template <class T, std::size_t M>
class cexpr_basic_string {
public:

    // An unsigned integral type used to represent sizes.
    using size_type = std::size_t;

    // The type of each character in the string (i.e., an alias for
    // the template parameter T).
    using value_type = T;

    // The type of a mutating pointer to each character in the string.
    using pointer = T*;

    // The type of a non-mutating pointer to each character in the
    // string.
    using const_pointer = const T*;

    // The type of a mutating reference to a character in the string.
    using reference = T&;

    // The type of a non-mutating reference to a character in the
    // string.
    using const_reference = const T&;

    // A mutating iterator type for the elements in the string.
    using iterator = pointer;

    // A non-mutating iterator type for the elements in the string.

    using const_iterator = const_pointer;

    // Default construct a string.
    // Creates an empty string (i.e., a string containing no
    // characters).
    //
    // Time complexity:
    // Linear in M.
    constexpr cexpr_basic_string()
            :   m_size_(0),
                m_str_(0) {}

    // Copy construct a string.
    //
    // Time complexity:
    // Linear in M.
    constexpr cexpr_basic_string(const cexpr_basic_string&) = default;

    // Copy assign a string.
    //
    // Time complexity:
    // Linear in M.
    constexpr cexpr_basic_string& operator=(const cexpr_basic_string&) = default;

    // Destroy a string.
    //
    // Time complexity:
    // Constant.
    ~cexpr_basic_string() = default;

    // Creates a string with the contents given by the
    // null-terminated character array pointed to by s.
    // If the string does not have sufficient capacity to hold
    // the character data provided, an exception of type
    // std::runtime_error is thrown.
    //
    // Time complexity:
    // Linear in the length of the string s.
    constexpr cexpr_basic_string(const value_type* s)
            :   m_size_(0),
                m_str_(0) {

        pointer curr(m_str_);
        while (*s != value_type(0)) {
            if (m_size_ == M) {
                throw std::runtime_error("insufficient capacity to hold the character data provided");
            }
            *curr++ = *s++;
            ++m_size_;
        }
    }

    // Creates a string with the contents specified by the characters
    // in the iterator range [first, last).
    // If the string does not have sufficient capacity to hold
    // the character data provided, an exception of type
    // std::runtime_error is thrown.
    //
    // Time complexity:
    // Linear in the size of the range [first, last).
    constexpr cexpr_basic_string(const_iterator first, const_iterator last)
            :   m_size_(0),
                m_str_(0) {

        pointer curr(m_str_);
        while(first != last) {
            if (m_size_ == M) {
                throw std::runtime_error("insufficient capacity to hold the character data provided");
            }
            *curr++ = *first++;
            ++m_size_;
        }
    }

    // Returns the maximum number of characters that can be held by a
    // string of this type.
    // The value returned is the template parameter M.
    //
    // Time complexity:
    // Constant.
    static constexpr size_type max_size() {
        return M;
    }

    // Returns the maximum number of characters that the string can
    // hold. The value returned is always the template parameter M.
    //
    // Time complexity:
    // Constant.
    constexpr size_type capacity() const {
        return M;
    }

    // Returns the number of characters in the string (excluding the
    // dummy null character).
    //
    // Time complexity:
    // Constant.
    constexpr size_type size() const {
        return m_size_;
    }

    // Returns a pointer to the first character in the string.
    // The pointer that is returned is guaranteed to point to a
    // null-terminated character array.
    // The user of this class shall not alter the dummy null
    // character stored at data() + size().
    //
    // Time complexity:
    // Constant.
    value_type* data() {
        return m_str_;
    }
    const value_type* data() const {
        return m_str_;
    }

    // Returns an iterator referring to the first character in the
    // string.
    //
    // Time complexity:
    // Constant.
    constexpr iterator begin() {
        return m_str_;
    }
    constexpr const_iterator begin() const {
        return m_str_;
    }

    // Returns an iterator referring to the fictitious
    // one-past-the-end character in the string.
    //
    // Time complexity:
    // Constant.
    constexpr iterator end() {
        return m_str_ + m_size_;
    }
    constexpr const_iterator end() const {
        return m_str_ + m_size_;
    }

    // Returns a reference to the i-th character in the string if i
    // is less than the string size; and returns a reference to the
    // dummy null character if i equals the string size.
    // Precondition: The index i is such that i >= 0 and i <= size().
    //
    // Time complexity:
    // Constant.
    constexpr reference operator[](size_type i) {
        assert(i >= 0 && i <= m_size_);
        return m_str_[i];
    }
    constexpr const_reference operator[](size_type i) const {
        assert(i >= 0 && i <= m_size_);
        return m_str_[i];
    }

    // Appends (i.e., adds to the end) a single character to the
    // string. If the size of the string is equal to the capacity,
    // the string is not modified and an exception of type
    // std::runtime_error is thrown.
    //
    // Time complexity:
    // Constant.
    constexpr void push_back(const T& x) {
        if (m_size_ == M) {
            throw std::runtime_error("insufficient capacity to hold the character provided");
        }
        m_str_[m_size_++] = x;
        m_str_[m_size_] = '\0';
    }

    // Erases the last character in the string.
    // If the string is empty, an exception of type std::runtime_error
    // is thrown.
    //
    // Time complexity:
    // Constant.
    constexpr void pop_back() {
        if (m_size_ == 0) {
            throw std::runtime_error("pop from empty string");
        }
        m_str_[--m_size_] = '\0';
    }

    // Appends (i.e., adds to the end) to the string the
    // null-terminated string pointed to by s.
    // Precondition: The pointer s must be non-null.
    // If the string has insufficient capacity to hold the new value
    // resulting from the append operation, the string is not modified
    // and an exception of type std::runtime_error is thrown.
    //
    // Time complexity:
    // Linear in the length of the string s.
    constexpr cexpr_basic_string& append(const value_type* s) {
        assert(s != nullptr);
        size_type s_len{0};
        for(const_pointer curr = s; *curr != '\0'; ++curr, ++s_len);
        if (s_len + m_size_ > M) {
            throw std::runtime_error("insufficient capacity to hold the character provided");
        }
        for (size_type i = 0; i < s_len; ++i) {
            m_str_[m_size_++] = s[i];
        } 
        m_str_[m_size_] = '\0';
        return *this;
    }

    // Appends (i.e., adds to the end) to the string another
    // cexpr_basic_string with the same character type (but
    // possibly a different maximum size).
    // If the string has insufficient capacity to hold the new value
    // resulting from the append operation, the string is not modified
    // and an exception of type std::runtime_error is thrown.
    //
    // Time complexity:
    // Linear in other.size().
    template <size_type OtherM>
    constexpr cexpr_basic_string& append(const cexpr_basic_string<value_type, OtherM>& other) {
        if (m_size_ + other.m_size_ > M) {
            throw std::runtime_error("insufficient capacity to hold the character provided");
        }
        for (std::size_t i = 0, other_size = other.size(); i < other_size; ++i) {
            m_str_[m_size_++] = other[i];
        } 
        m_str_[m_size_] = '\0';
        return *this;
    }

    // Erases all of the characters in the string, yielding an empty
    // string.
    //
    // Time complexity:
    // Constant.
    constexpr void clear() {
        m_size_ = 0;
        m_str_[0] = '\0';
    }

private:
    size_type m_size_;
    value_type m_str_[M + 1];
};

template <std::size_t M>
using cexpr_string = cexpr_basic_string<char, M>;

constexpr std::size_t to_string(std::size_t n, char* buffer, std::size_t size, char** end);

}
