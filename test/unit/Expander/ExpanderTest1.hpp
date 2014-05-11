#ifndef _EXPANDERTEST1_HPP_
#define _EXPANDERTEST1_HPP_

#include <gtest/gtest.h>
#include <Common/Window.hpp>
#include <BlendInt/Core/Object.hpp>

class ExpanderTest1: public testing::Test
{
public:
	ExpanderTest1 ();
	virtual ~ExpanderTest1 ();

protected:

	virtual void SetUp ()
	{
#ifdef DEBUG
		ASSERT_TRUE(BlendInt::Object::CheckAllocatedObjects());
#endif
	}

	virtual void TearDown ()
	{
#ifdef DEBUG
		ASSERT_TRUE(BlendInt::Object::CheckAllocatedObjects());
#endif
	}
};

#endif  // _EXPANDERTEST1_HPP_