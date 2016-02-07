#include "KSEntity.h"

KS_CORE_CONTAINER_BEGIN

#define ENTITY_COMPONENT_INIT_SIZE	4

Entity::Entity(void)
{
	mComponents.reserve(ENTITY_COMPONENT_INIT_SIZE);
}

Entity::~Entity(void)
{
	mComponents.clear();
}

KS_CORE_CONTAINER_END

