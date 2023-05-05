
#ifndef GSLIB_SHARED_PTR_HPP
#define GSLIB_SHARED_PTR_HPP

#include <iostream>

namespace gsl {
    template<typename T>
    class SharedPtr {
    public:

        SharedPtr() : _block(nullptr) {}

        explicit SharedPtr(T *ptr) : _block(new control_block <T>{1, *ptr}) {}

        SharedPtr(const SharedPtr &r) {
            _block = r._block;
            ++_block->counter;
        }

        SharedPtr(SharedPtr &&r) noexcept {
            _block = r._block;
            r._block = nullptr;
        }

        ~SharedPtr() {
            if (_block->counter > 1)
                --_block->counter;
            else {
                delete _block;
            }
        }

        auto operator=(const SharedPtr &r) -> SharedPtr & {
            _block = r._block;
            ++_block->counter;
            return *this;
        }

        auto operator=(SharedPtr &&r) noexcept -> SharedPtr & {
            _block = r._block;
            delete r._block;
            return *this;
        }

        explicit operator bool() const {
            return _block != nullptr;
        }

        auto operator*() const -> T & {
            return _block->object;
        }

        auto operator->() const -> T * {
            return &_block->object;
        }

        auto get() -> T * {
            return *_block->object;
        }

        void reset() {
            if (_block != nullptr)
                _block = nullptr;
        }

        void reset(T *ptr) {
            if (_block->counter == 1) {
                delete _block;
                _block->counter = 1;
                _block->object = *ptr;
            } else {
                --_block->counter;
                _block = new control_block <T>{1, *ptr};
            }
        }

        void swap(SharedPtr &r) {
            if (_block != r._block)
                std::swap(_block, r._block);
        }

        auto use_count() const -> size_t {
            return _block->counter;
        }

    private:
        template<typename U>
        struct control_block {
            size_t counter;
            U object;
        };

        control_block<T> *_block = nullptr;

        explicit SharedPtr(control_block<T> *storage_ptr) : _block(storage_ptr) {}

        template<typename U, typename ...Args>
        friend SharedPtr<U> makeShared(Args &&...args);
    };

    template<typename U, typename... Args>
    SharedPtr<U> makeShared(Args &&... args) {
        auto ptr = new typename SharedPtr<U>::template control_block<U>{1, U(std::forward<Args>(args)...)};
        return SharedPtr<U>(ptr);
    }
}

#endif //GSLIB_SHARED_PTR_HPP
