#include <bits/stdc++.h>
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

        cout << "\n"
             << channelName
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