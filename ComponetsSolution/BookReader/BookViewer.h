#include "pch.h" 

namespace BookReader
{
	public ref class BookViewer sealed : public Windows::UI::Xaml::Controls::Grid
	{ 
#pragma region MainView
	public:
	
		BookViewer();

		property Platform::Object^ DataSource
		{
			void set(Platform::Object^ value)
			{
				this->_datasource = (BookData::BookDataSource^)value ;
				loaddata() ;
			}
			Platform::Object^ get(){return this->_datasource ;}
		}

	private:
		BookData::BookDataSource^ _datasource ;


		Windows::UI::Xaml::Controls::StackPanel^ _contentpanel ;
		Windows::UI::Xaml::Controls::ScrollViewer^ _contentpanelscroll ;
		Windows::UI::Xaml::Media::CompositeTransform ^ _contentpaneltransform ;
		/// Main Window and BackGround
		void initcontrols();
		void loaddata();// to load the data into de datasource

		void ContentPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void ContentPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);	
		void ContentPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void ContentPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void ContentPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

#pragma endregion

#pragma region Background

	public:

		property Platform::String^ BackgroundItemSource
		{
			void set(Platform::String^ value)
			{ this->_dynamicbackground->SourcePath = value  ;	}	
			Platform::String^ get()
			{ return this->_dynamicbackground->SourcePath ; }
		}

		property float64 BackgroundItemWidth
		{
			void set(float64 value){ this->_dynamicbackground->ItemWidht =  value ; }
			float64 get(){return this->_dynamicbackground->ItemWidht ;}
		}

		property float64 BackgroundItemHeight
		{
			void set(float64 value){ this->_dynamicbackground->ItemHeight =  value ; }
			float64 get(){return this->_dynamicbackground->ItemHeight ;}
		}
  
	private:
		DynamicBackground ^ _dynamicbackground ;  
		Windows::UI::Xaml::Controls::StackPanel^ _backgroundpanel  ;
		Windows::UI::Xaml::Controls::ScrollViewer^ _backgroundpanelscroll ;
		Windows::UI::Xaml::Media::CompositeTransform ^ _backgroundpaneltransform ;   
#pragma endregion

	};
}