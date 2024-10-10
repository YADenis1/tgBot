#include <stdio.h>
#include <tgbot/tgbot.h>
using namespace TgBot;
using namespace std;

int main() {
    TgBot::Bot bot("5754837263:AAErExq127fiwhAvTB5h2-YPgEZyDA7a92k");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
        });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            bot.getApi().sendMessage(message->chat->id, "Bot working!");
            return;
        }
        if (StringTools::startsWith(message->text, "/day")) {
            bot.getApi().sendPhoto(message->chat->id, InputFile::fromFile("1.png", "image/png"));
            return;
        }
        });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}