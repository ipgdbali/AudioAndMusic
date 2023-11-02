2023-10-27 :
	There is problem with Cpointer_deleter which cannot fit well with std::vector.
	std::vector needs it class to have copy constractor enabled.
	Solution that provide is : 
	change Cpointer_deleter into structure as param.
	Then on delete use another method to delete it. 
2023-10-30
Adds std::vector in CAbsStreamProducer to delete all instance of eWrapParam

static variable pada virtual noexcept final std::pair

branch / change
- remove std::pair in oscilator

Feature

next commit :
removing COscilatorFunc.h