#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

class EventHub
{
public:
    using EventCallback = std::function<void(const std::vector<void*>&)>;

    // Subscribe to an event
    static void Subscribe(const std::string& eventName, EventCallback callback)
    {
        listeners[eventName].push_back(callback);
    }

    // Unsubscribe from an event
    static void Unsubscribe(const std::string& eventName, EventCallback callback)
    {
        auto& callbacks = listeners[eventName];
        callbacks.erase(
            std::remove_if(callbacks.begin(), callbacks.end(),
                [&callback](const EventCallback& cb) {
                    return cb.target_type() == callback.target_type();
                }),
            callbacks.end()
        );
    }

    // Trigger an event with multiple arguments (if any)
    static void Trigger(const std::string& eventName)
    {
        // Trigger the event with an empty vector if no arguments are passed
        TriggerWithData(eventName, {});
    }

    // Trigger an event with multiple arguments (if any)
    static void Trigger(const std::string& eventName, const std::vector<void*>& args)
    {
        // Trigger the event with the provided arguments
        TriggerWithData(eventName, args);
    }

private:
    static void TriggerWithData(const std::string& eventName, const std::vector<void*>& args)
    {
        auto it = listeners.find(eventName);
        if (it != listeners.end())
        {
            for (const auto& callback : it->second)
            {
                callback(args);
            }
        }
    }

private:
    static std::unordered_map<std::string, std::vector<std::function<void(const std::vector<void*>&)>>> listeners;
};

// Define the static member variable


/*void OnCustomEvent(const std::vector<void*>& args)
{
    if (args.empty())
    {
        std::cout << "Received event with no data." << std::endl;
    }
    else
    {
        if (args.size() >= 2)
        {
            // Cast arguments back to their correct types
            int* number = static_cast<int*>(args[0]);
            std::string* text = static_cast<std::string*>(args[1]);

            // Use the casted values
            std::cout << "Received event with values: " << *number << ", " << *text << std::endl;
        }
    }
}

int main()
{
    // Subscribe to an event
    EventHub::Subscribe("TestEvent", OnCustomEvent);

    // Trigger the event with multiple values
    int number = 100;
    std::string text = "hello";
    EventHub::Trigger("TestEvent", { &number, &text });

    // Trigger the event with no data
    EventHub::Trigger("TestEvent");

    return 0;
}*/


