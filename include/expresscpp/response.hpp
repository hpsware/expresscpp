#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "boost/beast/http/message.hpp"
#include "boost/beast/http/string_body.hpp"
#include "boost/uuid/uuid.hpp"

namespace expresscpp {

class Session;

class Response {
 public:
  explicit Response(Session* session);

  void SetStatus(const uint16_t status);
  void SetHeader(const std::string& key, const std::string& value);

  void KeepAlive(bool alive);

  void Send(std::string message);
  void Send();

  void Json(std::string_view json_string);

  bool ResponseSent() const;

 public:
  boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, 11};
  void SendInternal();

  Session* session_{nullptr};
  bool response_sent_{false};

 private:
  uint16_t status_{200u};
  boost::uuids::uuid uuid_;
  bool costum_status_code_{false};
};

typedef std::shared_ptr<Response> response_t;

}  // namespace expresscpp
