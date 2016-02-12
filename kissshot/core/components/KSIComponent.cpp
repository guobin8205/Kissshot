#include "KSIComponent.h"
#include "container/KSEntity.h"

KS_USE_COMPONENT;

IComponent::~IComponent()
{
	setOwner(nullptr);
}

void IComponent::setOwner(std::shared_ptr<KS_CORE::container::Entity> other)
{
	if (other.get() == mOwner) return;

	auto owner = mOwner;
	mOwner = nullptr;
	std::shared_ptr<IComponent> result = nullptr;

	if (owner)
		result = owner->removeComponent(CLASS_PTR_HASH(this), mUid);

	if (other && result)
	{
		other->addComponent(result);
	}
	mOwner = other.get();
}

void IComponent::destoryInEntity(void)
{
	setOwner(nullptr);
}
