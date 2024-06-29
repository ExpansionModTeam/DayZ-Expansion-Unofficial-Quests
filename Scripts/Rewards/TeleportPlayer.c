class CustomMission: MissionServer
{
    override void Expansion_OnQuestCompletion(ExpansionQuest quest)
    {
        super.Expansion_OnQuestObjectivesComplete(quest);

        switch (quest.GetQuestConfig().GetID())
        {
            case 40: // Quest ID 40
                // You can give a list of potential positions 
                array<vector> teleportPositions = {"4557.369629 126.911789 6560.999023", "4560.369629 126.911789 6560.999023"};
                TeleportPlayerAt(quest, teleportPositions);
            break;
            case 42: // Quest ID 42
                // or just give one position like this
                TeleportPlayerAt(quest, "0 0 0");
            break;
        }

        super.Expansion_OnQuestCompletion(quest);
    }

    bool TeleportPlayerAt(ExpansionQuest quest, array<vector> pos)
    {
        return TeleportPlayerAt(quest, pos.GetRandomElement());
    }

    bool TeleportPlayerAt(ExpansionQuest quest, vector pos)
    {
        PlayerBase player = quest.GetPlayer();
        if (!player)
            return false;

        vector ori = player.GetOrientation();
        DayZPlayerSyncJunctures.ExpansionTeleport(player, pos, ori);

        return true;
    }
};
