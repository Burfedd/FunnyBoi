#include "FunnyBoi.h"

const std::string BOT_TOKEN = "bot token";
const std::string GUILD_ID = "guild id";

int main()
{
	// Random
	std::random_device r_device;
	std::mt19937 rng(r_device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

	// Bot
	dpp::cluster bot(BOT_TOKEN);

	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("/tts test");
		}
	});

	bot.on_message_create([&dist, &rng, &bot](const dpp::message_create_t& event) {
		if (event.msg.author != bot.me.id) {
			int generated = dist(rng);
			if (generated >= 50) {
				event.reply("Random reply");
			}
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(
				dpp::slashcommand("ping", "/tts test", bot.me.id)
			);
		}
	});

	bot.start(false);
}
