//
// TestPage.xaml.h
// Declaration of the TestPage class
//

#pragma once

#include "TestPage.g.h"

namespace BookReader
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class TestPage sealed
	{
	public:
		TestPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		BookData::BookDataSource^ _book1 ;
		Platform::Collections::Vector<Platform::String^>^ paths1 ;
		Platform::Collections::Vector<Platform::String^>^ paths2 ;
		void loadbook1();
	};
}
