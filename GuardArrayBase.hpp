#ifndef GuardArrayBase_hpp
#define GuardArrayBase_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "IndexProvider.hpp"

//-----------------------------------------------------------------------------
//                            class GuardArrayBase

template<typename T>
class GuardArrayBase {
public:
    template<typename U, int N>
    friend class IndexProvider;
    
private:
    GuardArrayBase();
    
protected:
	int dementionCount;         // a[1][2][3][4][5] dementionCount = 5;
	size_t *dementions;         // a[1][2][3][4][5] dementions[0] = 1; dementions[1] = 5; dementions[2] = 20; dementions[3] = 60;

    T*   array;
    bool isAlloc;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    
public:
	GuardArrayBase(int dementionCount)
	: dementionCount(dementionCount), dementions(new size_t[dementionCount+1])
	{
	}

	GuardArrayBase(const GuardArrayBase& gt)
	: TRACE_STRING_SAVE_DECLARE(id(GT::GetNewIdByIncreaseId(gt.id)))
	isAlloc(true), dementionCount(gt.dementionCount)
	{
			for (int i = 0; i <= dementionCount; i++) {
			this->dementions[i] = gt.dementions[i];
		}
		size_t elementCount = this->dementions[dementionCount];
		this->array = new T[elementCount];

		T* begin = this->array;
		T* end = begin + elementCount;
		T* source = gt.array;
		for (; begin != end; begin++, source++) {
			*begin = *source;
		}
	}

    ~GuardArrayBase() {
		delete[] dementions;
        if(isAlloc) {
            delete[] this->array;
        }
	}

	void AllocWithDementions() {
		this->dementions[0] = 1;
		for (int i = 0; i < dementionCount; i++) {
			this->dementions[i + 1] *= this->dementions[i];
		}

		if (this->isAlloc == false) return;
		size_t allElement = this->dementions[dementionCount];
		this->array = new T[allElement]();
	}

	void InitDementions() {
		this->dementions[0] = 1;
		for (int i = 0; i < dementionCount; i++) {
			this->dementions[i + 1] *= this->dementions[i];
		}

		if (this->isAlloc == false) return;
		size_t allElement = this->dementions[dementionCount];
		this->array = new T[allElement];

		T* begin = array;
		T* end = begin + allElement;
		T* source = array;
		for (; begin != end; begin++, source++) {
			*begin = *source;
		}
	}

	friend std::istream& operator >> (std::istream &   si,
										GuardArrayBase& gt) {
		T data;
		if (GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
			if (typeid(si) == typeid(std::cin)) {
				std::cout << "Please input ";
				std::cout << "[" << gt.size() << "] Datas "
					<< gt.id << ": " << std::endl;
			}
		}
		T * arr = gt.array;
		for (int i = 0; i<gt.dementions[gt.dementionCount]; i++) {
			si >> data;
			arr[i] = data;
		}
		return si;
	}

	friend std::ostream& operator << (std::ostream &        so,
										const GuardArrayBase& gt) {
		T* p = gt.array;
		T* end = p + gt.dementions[gt.dementionCount];
		while (p < end)
		{
			for (int i = 0; i<gt.dementions[1]; i++) {
				so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
					<< " " << *p++ << " ";
			}
			so << std::endl;
		}
		so << std::endl;
		return so;
	}
};

#endif /* GuardArrayBase_hpp */
