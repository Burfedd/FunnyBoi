#include "FunnyBoi.h"

const std::string BOT_TOKEN = "bot token";
const std::string GUILD_ID = "guild id";

int main()
{
	dpp::cluster bot(BOT_TOKEN);
	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(
				dpp::slashcommand("ping", "Ping Pong!", bot.me.id)
			);
		}
	});

	bot.start(false);
}
