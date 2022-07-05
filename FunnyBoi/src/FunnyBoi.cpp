#include "FunnyBoi.h"

int main(int argc, char* argv[])
{
	// Random
	std::random_device r_device;
	std::mt19937 rng(r_device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

	// Bot
	dpp::cluster bot(argv[1]);
	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([&dist, &rng](const dpp::slashcommand_t& event) {
		std::string cmd = event.command.get_command_name();
		if (cmd == "ping") {
			event.reply("Pong!");
		} else if (cmd == "roll") {
			int generated = dist(rng);
			event.reply(event.command.msg.author.username + " rolled " + std::to_string(generated));
		}
	});

	bot.on_message_create([&dist, &rng, &bot](const dpp::message_create_t& event) {
		if (event.msg.author != bot.me.id) {
			int generated = dist(rng);
			if (generated == 25) {
				event.reply("Rot zakroj");
			}
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(
				dpp::slashcommand("roll", "Rolling a number", bot.me.id)
			);
			bot.global_command_create(
				dpp::slashcommand("ping", "Ping-pong test", bot.me.id)
			);
		}
	});

	bot.start(false);
}
