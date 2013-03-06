//
// StackTest.xaml.h
// Declaration of the StackTest class
//

#pragma once

#include "StackTest.g.h"

namespace BookReader
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class StackTest sealed
	{
	public:
		StackTest();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void loaddata();
		Platform::Collections::Vector<Platform::String^> ^paths1 ;	
	};
}
