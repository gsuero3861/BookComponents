#include "pch.h"
#include <math.h>

namespace BookReader
{
	public enum class ItemsScrollState
	{
		Enable,
		Dislable
	};

	public ref class StackSlider sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		StackSlider();

#pragma region Stacks 
	public:
		property Windows::Foundation::Collections::IVector<BookData::StackDataSource^>^ DataSource
		{
			void set( Windows::Foundation::Collections::IVector<BookData::StackDataSource^>^ value)
			{
				this->_datasource =  value ;
				loadstacks() ;
			}
			Windows::Foundation::Collections::IVector<BookData::StackDataSource^>^ get(){ return this->_datasource ; };
		}

		property float64 StackItemWith
		{
			void set(float64 value){this->_stackitemwidth =  value ;}
			float64 get(){return this->_stackitemwidth ;}
		}

		property float64 StackItemHeight
		{
			void set(float64 value){ this->_stackitemheight =  value ; }
			float64 get(){return this->_stackitemheight  ;}
		}

	private:
		Windows::Foundation::Collections::IVector<BookData::StackDataSource^> ^ _datasource ;
		float64 _stackitemheight, _stackitemwidth ;
		int32 _currentstack, _currentstackitem ;//start at 0,1,2...


		Windows::UI::Xaml::Controls::ScrollViewer^ _itemsscroll ;
		Windows::UI::Xaml::Controls::StackPanel^ _itemspanel ;
		Windows::UI::Xaml::Controls::Grid^ _gridstacks ;
		void initstackscontrols();
		void loadstacks() ;
		//to control the stack is being manipulated
		void StackManipulationStarted_1(Platform::Object ^ sender , int32 args);
		void StackManipulationFinished_1(Platform::Object ^ sender , int32 stacknumber, int32 citem); 
		void StackAnimationCompleted_1(Platform::Object ^ sender , int32 stacknumber);

#pragma endregion

#pragma region Slider

		 
		Windows::UI::Xaml::Controls::Grid^ _gridslider ;
		SlideViewer ^ _slider ;

		void initslidercontrols();

#pragma endregion
	};
}