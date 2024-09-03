#ifndef LIST_HPP
#define LIST_HPP

#include "container.hpp"

namespace Vessel {

template <typename PType>
concept IsListSubTypesAvailable = requires {
  requires IsContainerSubTypesAvailable<PType>;
  requires IsComparable<typename PType::ValueType>;
  requires IsSameType<typename PType::KeyType, typename PType::SizeType>;
};

/// A container with element arranged in series.
template <typename PType>
concept IsList = requires {
  requires IsListSubTypesAvailable<PType>;
  requires IsContainer<PType>;
  requires IsComparable<PType>;

  {
    declval<const PType>().slice(declval<typename PType::KeyType>(),
                                 declval<typename PType::KeyType>())
  } -> IsSameType<PType>;
  {
    declval<PType>() << declval<typename PType::ValueType>()
  } -> IsSameType<PType &>;
  {
    declval<PType>().push_back(declval<typename PType::ValueType>())
  } -> IsSameType<void>;
  {
    declval<PType>().push_front(declval<typename PType::ValueType>())
  } -> IsSameType<void>;
  { declval<PType>().pop_back() } -> IsSameType<typename PType::ValueType>;
  { declval<PType>().pop_front() } -> IsSameType<typename PType::ValueType>;
};

} // namespace Vessel

#endif // LIST_HPP