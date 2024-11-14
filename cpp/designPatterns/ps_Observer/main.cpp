#include <print>
#include <functional>
#include <map>

using namespace std;

using EventHandle = unsigned int;

template<typename... Args>
class Event final
{
public:
   // Adds an observer. Returns an EventHandle to unregister the observer.
   [[nodiscard]] EventHandle addObserver(function<void(const Args &...)> observer)
   {
      auto number{++counter_};
      observers_[number] = std::move(observer);
      return number;
   }

   // Unregisters the observer pointed to by the given handle.
   void removeObserver(EventHandle handle)
   {
      observers_.erase(handle);
   }

   // Raise event: notifies all registered observers.
   void raise(const Args &... args)
   {
      for (const auto &[_, callback]: observers_)
      {
         callback(args...);
      }
   }

private:
   unsigned int counter_{0};
   map<EventHandle, function<void(const Args &...)>> observers_;
};


class ObservableSubject
{
public:
   EventHandle registerDataModifiedObserver(const auto &observer)
   {
      return eventDataModified_.addObserver(observer);
   }

   void unregisterDataModifiedObserver(EventHandle handle)
   {
      eventDataModified_.removeObserver(handle);
   }

   EventHandle registerDataDeletedObserver(const auto &observer)
   {
      return eventDataDeleted_.addObserver(observer);
   }

   void unregisterDataDeletedObserver(EventHandle handle)
   {
      eventDataDeleted_.removeObserver(handle);
   }

   void modifyData()
   {
      // ...
      eventDataModified_.raise(1, 2.3);
   }

   void deleteData()
   {
      // ...
      eventDataDeleted_.raise();
   }

private:
   Event<int, double> eventDataModified_;
   Event<> eventDataDeleted_;
};


void modified(int a, double b)
{
   println("modified({}, {})", a, b);
}


class Observer final
{
public:
   explicit Observer(ObservableSubject &subject) : subject_{subject}
   {
      subjectModifiedHandle_ = subject_.registerDataModifiedObserver(
          [this](int i, double d)
          { onSubjectModified(i, d); }
      );
   }

   ~Observer()
   {
      subject_.unregisterDataModifiedObserver(subjectModifiedHandle_);
   }

private:
   void onSubjectModified(int a, double b)
   {
      println("Observer::onSubjectModified({}, {})", a, b);
   }

   ObservableSubject &subject_;
   EventHandle subjectModifiedHandle_;
};


int main()
{
   ObservableSubject subject;

   auto handleModified{
       subject.registerDataModifiedObserver(modified)
   };
   auto handleDeleted{
       subject.registerDataDeletedObserver(
           []
           { println("deleted"); })
   };

   Observer observer{subject};

   subject.modifyData();
   subject.deleteData();

   println("");

   subject.unregisterDataModifiedObserver(handleModified);
   subject.modifyData();
   subject.deleteData();
}