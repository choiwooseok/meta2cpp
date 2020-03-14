#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace test {
namespace examples {

class Response {
public:
    Response() = default;
    Response(const Response&) = default;
    Response(Response&&) = default;
    Response& operator=(const Response&) = default;
    Response& operator=(Response&&) = default;
    virtual ~Response() = default;

private:
    /**
    * fieldName : code
    * fieldDesc : 
    */
    std::string code;

public:
    std::string getCode();
    void setCode(const std::string& code);

private:
    /**
    * fieldName : name
    * fieldDesc : 
    */
    std::string name;

public:
    std::string getName();
    void setName(const std::string& name);

private:
    /**
    * fieldName : desc
    * fieldDesc : 
    */
    std::string desc;

public:
    std::string getDesc();
    void setDesc(const std::string& desc);

public:
    virtual std::string toString();
    void fromJson(boost::property_tree::ptree& json);
};
} /* namespace test */
} /* namespace examples */

#endif /* RESPONSE_H_ */
