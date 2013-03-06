#include "pch.h"
 
Object^ BookReader::ParallaxConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return (double)value * _factor ;
}
 
Object^ BookReader::ParallaxConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return (double)value / _factor ;
}