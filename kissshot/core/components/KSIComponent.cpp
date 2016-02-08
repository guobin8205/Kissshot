#include "KSIComponent.h"
#include "container/KSEntity.h"

KS_USE_COMPONENT;

IComponent::~IComponent()
{
	setOwner(nullptr);
}

void IComponent::setOwner(::kissshot::core::container::Entity * other)
{
	if (other == mOwner) return;

	auto owner = mOwner;
	mOwner = nullptr;
	std::shared_ptr<IComponent> result = nullptr;

	if (owner)
		result = owner->removeComponent(this);

	if (other && result)
	{
		other->addComponent(result);
	}
	mOwner = other;
}
