#include <memory>
class Any;
class _any_data_implement
{
public:
    _any_data_implement()= default;
    virtual ~_any_data_implement()
    {

    }
};
template<typename T>
class _any_data:public _any_data_implement
{
    template<typename U>
    friend U& Any_cast(const Any& _any);
public:
    template<typename U>
    _any_data(U&& value):_value(value)
    {

    }
    ~_any_data()
    {

    }
private:
    T _value;
};
template<typename T,typename U>
struct is_not_Any
{
    static const bool value = true;
    using type = U;
};
template<typename U>
struct is_not_Any<Any,U>
{
    static const bool value = false;
};
template<typename U>
struct is_not_Any<Any&,U>
{
    static const bool value = false;
};
template<typename U>
struct is_not_Any<Any&&,U>
{
    static const bool value = false;
};
class Any
{
    template<typename U>
    friend U& Any_cast(const Any& _any);
public:
    Any(Any& _any):_data_hold(_any._data_hold)
    {

    }
    Any(const Any& _any):_data_hold(_any._data_hold)
    {

    }
    Any(Any&& _any) :_data_hold(_any._data_hold)
    {
        _any._data_hold.reset();
    }
    template<typename T>
    Any(T&& value):_data_hold(std::make_shared<_any_data<typename std::decay<T>::type>>(std::forward<typename std::decay<T>::type>(value)))
    {

    }

    Any& operator=(const Any& _any)
    {
        if(this!=&_any)
        {
            _data_hold.reset();
            _data_hold = _any._data_hold;
        }
        return *this;
    }

    ~Any()
    {
    }
private:
    std::shared_ptr<_any_data_implement> _data_hold;
};
template<typename T>
T& Any_cast(const Any& _any)
{
    auto _v = static_cast<_any_data<T>*>(_any._data_hold.get());
    return _v->_value;
}
