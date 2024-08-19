#ifndef HOLDER_HPP
#define HOLDER_HPP

#include "def.hpp"

namespace Vessel {

template <typename PType>
concept IsReleaser =
    IsInconstructible<PType> && IsValueTypeAvailable<PType> && requires {
      {
        PType::release(declval<typename PType::ValueType *>())
      } -> IsSameType<void>;
    };

template <typename PType> struct Releaser : public Inconstructible<> {
  using ValueType = PType;
  static auto release(ValueType *p_pointer) -> void { delete p_pointer; }
};

template <typename PType> struct Releaser<PType[]> : public Inconstructible<> {
  using ValueType = PType;
  static auto release(ValueType *p_pointer) -> void { delete[] p_pointer; }
};
static_assert(IsReleaser<Releaser<DummyScalar>>);

template <typename PType>
concept IsHolderSubTypesAvailable = requires {
  typename PType::ReleaserType;
} && IsValueTypeAvailable<PType> && IsReleaser<typename PType::ReleaserType>;

template <typename PType>
concept IsHolder = IsHolderSubTypesAvailable<PType> && requires {
  { PType(declval<typename PType::ValueType *>()) } -> IsSameType<PType>;
  { declval<PType>().operator->() } -> IsSameType<typename PType::ValueType *>;
  {
    declval<const PType>().operator->()
  } -> IsSameType<const typename PType::ValueType *>;
  { *declval<PType>() } -> IsSameType<typename PType::ValueType &>;
  { *declval<const PType>() } -> IsSameType<const typename PType::ValueType &>;
};

} // namespace Vessel

#endif // HOLDER_HPP