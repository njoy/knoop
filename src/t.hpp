#ifndef KNOOP_HPP
#define KNOOP_HPP

#include <map>
#include <variant>
#include <list>

#include <range/v3/all.hpp>

#include <experimental/optional>
namespace std { using namespace std::experimental; }

#include "value-ptr.hpp"

namespace njoy {
namespace knoop {
  #include "knoop/Node.hpp"
}
}

#endif // KNOOP_HPP
