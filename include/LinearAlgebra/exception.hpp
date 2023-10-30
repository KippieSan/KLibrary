#ifndef exception_hpp
#define exception_hpp
#include <string>
#include <sstream>
class Exception {
    private:
        static constexpr std::string_view terminate_ = "terminate called after throwing instance of ";
        static constexpr std::string_view undefined_ = "unknown exception called.";
    
    protected:
        std::string message_;

        Exception(const std::string& message) : message_(message){}

        static constexpr std::string_view terminate() noexcept { return terminate_; }
        static constexpr std::string_view undefined() noexcept { return undefined_; }
    
    public:
        virtual const std::string what() const noexcept {
            std::stringstream ss;
            ss << terminate() << this->message_ << std::endl;
            return ss.str();
        }
};
#endif // exception_hpp
