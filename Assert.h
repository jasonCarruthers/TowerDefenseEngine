#ifndef ASSERT_HFILE
#define ASSERT_HFILE


/*
* Global function prototypes
*/
extern void AssertTrue(bool boolExpression, const std::string& fatalMessage);
extern void AssertFalse(bool boolExpression, const std::string& fatalMessage);


#endif /*ASSERT_HFILE*/