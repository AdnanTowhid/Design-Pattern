# Lab 03 -- Observer Pattern

## 1. Pattern Name

**Observer Design Pattern**

## 2. Category

**Behavioral Design Pattern**

The Observer Pattern is a Behavioral Design Pattern. It defines a relationship between objects where a change in one object automatically causes updates or notifications to other dependent objects.

## 3. Intent

The main intent of the Observer Pattern is to establish a one-to-many dependency between objects. When the state of one object changes, all of its registered observers are automatically notified and updated.

In this project, a YouTube channel acts as the Subject. Subscribers observe the channel, and whenever a new video is uploaded, all subscribers automatically receive a notification.

## 4. Problem Statement

Suppose a YouTube channel has many subscribers:
```
YouTube Channel
 |
 +---- Subscriber 1
 +---- Subscriber 2
 +---- Subscriber 3
 +---- Subscriber 4
```
Whenever the channel uploads a new video, all subscribers should be notified.

The problem is:
> How can the channel notify multiple subscribers automatically without creating a tightly coupled system?

If the YouTube channel directly depends on every specific subscriber class, the system becomes rigid, hard to extend, and difficult to maintain. The Observer Pattern solves this problem by allowing subscribers to register themselves as observers through an abstract interface.

## 5. Motivation

The motivation for using the Observer Pattern is to create a decoupled notification system where one object can notify many other objects automatically.

For example:
```
New Video Uploaded
        ↓
 YouTube Channel
        ↓
     notify()
     /  |  \
    ↓   ↓   ↓
 User1 User2 User3
    ↓   ↓   ↓
 Notify Notify Notify
```

The YouTube channel does not need to know the detailed implementation of each subscriber. It only needs to notify registered observer references via the common interface.

## 6. Pattern Structure (UML Class Diagram)

> **UML diagram:** Add the Observer Pattern UML image pushed by the team to the repository and update the filename below.
>
> `![Observer Pattern UML](path/to/observer-pattern-uml.png)`

## 7. Class Responsibilities

-   **Observer (Interface)** -- Abstract interface declaring notification updates.
    -   Define the `update(video)` operation.
    -   Provide a common interface for all observers.
    -   Allow different types of observers to receive notifications polymorphically.
-   **Subscriber (Concrete Observer)** -- Implements the `Observer` interface.
    -   Store subscriber name and details.
    -   Implement the `update(video)` function.
    -   Display notification messages when a new video is uploaded.
-   **YouTubeChannel (Subject)** -- The observable Subject.
    -   Store the channel name.
    -   Maintain a list of registered subscribers.
    -   Allow subscribers to subscribe and register.
    -   Upload new videos.
    -   Notify all registered subscribers upon changes.
-   **Subscriber List** -- Collection storing pointers to registered observers (`vector<Observer*>`).
    -   Maintain registered observer instances.
    -   Allow the channel to iterate and notify every subscriber.

## 8. Code Implementation

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ===============================
// OBSERVER INTERFACE
// ===============================
class Observer {
public:
    virtual void update(string video) = 0;
    virtual ~Observer() {}
};

// ===============================
// CONCRETE OBSERVER
// ===============================
class Subscriber : public Observer {
private:
    string name;

public:
    Subscriber(string name) {
        this->name = name;
    }

    void update(string video) override {
        cout << name
             << " received notification: New video -> "
             << video << endl;
    }
};

// ===============================
// SUBJECT
// ===============================
class YouTubeChannel {
private:
    string channelName;
    vector<Observer*> subscribers;

public:
    YouTubeChannel(string name) {
        channelName = name;
    }

    // Subscribe a user
    void subscribe(Observer* observer) {
        subscribers.push_back(observer);
        cout << "New subscriber added!\n";
    }

    // Upload new video
    void uploadVideo(string video) {
        cout << "\n" << channelName
             << " uploaded: "
             << video << endl;
        notifySubscribers(video);
    }

    // Notify all subscribers
    void notifySubscribers(string video) {
        for (Observer* observer : subscribers) {
            observer->update(video);
        }
    }
};

// ===============================
// MAIN
// ===============================
int main() {
    cout << "----- YouTube Notification System -----\n\n";

    // Create YouTube channel
    YouTubeChannel channel("Adnan Tech");

    // Create subscribers
    Subscriber user1("Rahim");
    Subscriber user2("Karim");
    Subscriber user3("Sakib");

    // Subscribe users
    channel.subscribe(&user1);
    channel.subscribe(&user2);
    channel.subscribe(&user3);

    // Upload videos
    channel.uploadVideo("C++ OOP Tutorial");
    channel.uploadVideo("Design Patterns Explained");

    return 0;
}
```

## 9. Execution Flow (Object Interaction)

1.  **Create YouTube Channel**: A `YouTubeChannel` object is created (`YouTubeChannel channel("Adnan Tech");`).
2.  **Create Subscribers**: Three subscriber objects (`Rahim`, `Karim`, and `Sakib`) are instantiated.
3.  **Subscribe**: The subscribers register with the channel:
    ```cpp
    channel.subscribe(&user1);
    channel.subscribe(&user2);
    channel.subscribe(&user3);
    ```
    The channel state becomes:
    ```
    YouTubeChannel
     |
     +---- Rahim
     +---- Karim
     +---- Sakib
    ```
4.  **Upload Video**: The channel uploads `"C++ OOP Tutorial"`.
5.  **Notify Subscribers**: The channel invokes `notifySubscribers(video)`. Every registered observer receives an update:
    ```
    YouTubeChannel
     |
     | notify
     ↓
     +---+---+---+
     ↓   ↓   ↓
    Rahim Karim Sakib
    ```
6.  **Subscribers Receive Notification**: Each subscriber executes its `update()` method and prints the notification message.

The overall interaction flow:
```
YouTube Channel
      ↓
 Upload Video
      ↓
notifySubscribers()
      ↓
Observer 1 → update()
Observer 2 → update()
Observer 3 → update()
```

## 10. Advantages

-   Provides loose coupling between the Subject and its Observers.
-   Supports dynamic one-to-many communication at runtime.
-   Observers can be registered or unregistered dynamically without modifying the Subject.
-   New observer types can be introduced easily by adhering to the `Observer` interface (Open/Closed Principle).
-   Automatically propagates state changes to all listening components.
-   Improves modularity, flexibility, and testability.

## 11. Limitations

-   A large number of observers can cause memory and performance overhead during bulk notifications.
-   Notifications may become difficult to track and debug in complex event cascades.
-   If observers depend heavily on the order of notifications, unexpected race conditions or behavior may occur.
-   Careless management of observer references can cause memory leaks or dangling pointers if observers are destroyed without unregistering.

## 12. Real-life Applications

-   **Video / Streaming Platforms**: YouTube, Twitch channel notifications and alerts.
-   **News & Content Platforms**: Subscriptions and newsletters.
-   **Social Media**: Notifications for likes, comments, and posts (Facebook, Twitter, Instagram).
-   **Financial Markets**: Real-time stock price monitoring and exchange feeds.
-   **Weather Monitoring**: Weather station sensor alerts.
-   **GUI Event Handling**: Button click listeners and window event dispatchers.
-   **Chat & Messaging**: Pub-Sub message broker systems.
-   **Real-time Dashboards**: Live telemetry metric updates.

## 13. Industry Examples

-   **YouTube** -- When a subscribed channel uploads a new video, subscribers receive notification pings across web and mobile.
-   **Stock Trading Applications** -- When a stock price changes, multiple client apps and portfolio trackers receive live ticker updates.
-   **GUI Applications** -- UI frameworks (Qt, JavaFX, React, DOM Event Listeners) notify registered event listeners when events occur.
-   **News Applications** -- When news outlets publish breaking stories, push notification services dispatch alerts to subscribed devices.
-   **Real-Time Dashboards** -- DevOps and APM dashboards observe metric streams and automatically refresh graphs in real time.

## 14. Conclusion

The Observer Pattern provides an efficient mechanism for implementing one-to-many communication between objects.

In this project, the `YouTubeChannel` acts as the Subject, while `Subscriber` objects act as Observers. When the channel uploads a new video, the channel automatically notifies all registered subscribers without hardcoded dependencies.

The project demonstrates important OOP concepts including abstraction, inheritance, polymorphism, encapsulation, and loose coupling. Therefore, the Observer Pattern is highly valuable for building extensible, event-driven systems.
