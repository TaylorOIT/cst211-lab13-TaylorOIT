#include "Exception.h"
#include<ostream>
#include <string> 

Exception::Exception(const char* msg) {

	m_msg = new char[strlen(msg) + 1];
	strcpy_s(m_msg, strlen(msg) + 1, msg);

}

Exception::~Exception() {
	delete[] m_msg;
}

const char* Exception::GetMessage() {

	return m_msg;
}

void Exception::SetMessage(const char* msg) {
	delete[] m_msg;
	m_msg = new char[strlen(msg) + 1];
	strcpy_s(m_msg, strlen(msg) + 1, msg);
}

Exception::Exception(Exception& copy) {

	m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy_s(m_msg, strlen(copy.m_msg) + 1, copy.m_msg);
}

Exception::Exception(Exception&& copy)
{
	m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy_s(m_msg, strlen(copy.m_msg) + 1, copy.m_msg);

	delete[] copy.m_msg;
	copy.m_msg = nullptr;

}

Exception& Exception::operator=(const Exception& rhs)
{
	if (this != &rhs)
	{
		delete[] m_msg;
		m_msg = nullptr;

		if (rhs.m_msg != nullptr)
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy_s(m_msg, strlen(rhs.m_msg) + 1, rhs.m_msg);
		}
	}
	return *this;
}

Exception& Exception::operator=(Exception&& rhs)
{

	delete[] m_msg;
	m_msg = nullptr;

	if (rhs.m_msg != nullptr)
	{
		m_msg = new char[strlen(rhs.m_msg) + 1];
		strcpy_s(m_msg, strlen(rhs.m_msg) + 1, rhs.m_msg);
	}


	rhs.m_msg = nullptr;
	return *(this);
}

std::ostream& operator<<(std::ostream& stream, const Exception& except)
{
	stream << except.m_msg << std::endl;
	return stream;
}
