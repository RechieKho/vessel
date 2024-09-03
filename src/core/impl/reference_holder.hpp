#ifndef IMPL_REFERENCE_HOLDER_HPP
#define IMPL_REFERENCE_HOLDER_HPP

#include "def.hpp"
#include "holder.hpp"

namespace Vessel {

template <typename PType>
concept IsReferenceHolder = requires {
  requires IsHolder<PType>;
  requires IsEqualityAvailable<PType>;
  requires IsCopyableFrom<PType>;
  requires IsMovableFrom<PType>;
};

template <typename PType, IsReleaser PReleaserType = Releaser<PType>>
class ReferenceHolder {
public:
  using ValueType = PType;
  using ReleaserType = PReleaserType;

private:
public:
  ReferenceHolder(ValueType *p_pointer) { throw UnimplementedException(); }

  ReferenceHolder(const ReferenceHolder &p_holder) = delete;

  ReferenceHolder(ReferenceHolder &&p_holder) {
    throw UnimplementedException();
  }

  auto operator->() -> ValueType * { throw UnimplementedException(); }

  auto operator->() const -> const ValueType * {
    throw UnimplementedException();
  }

  auto operator*() -> ValueType & { throw UnimplementedException(); }

  auto operator*() const -> const ValueType & {
    throw UnimplementedException();
  }
};

} // namespace Vessel

#endif // IMPL_REFERENCE_HOLDER_HPP