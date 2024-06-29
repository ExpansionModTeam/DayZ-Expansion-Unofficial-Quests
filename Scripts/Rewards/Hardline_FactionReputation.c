class CustomMission: MissionServer
{
    override void Expansion_OnQuestCompletion(ExpansionQuest quest)
    {
        super.Expansion_OnQuestCompletion(quest);

        int factionID;
        switch (quest.GetQuestConfig().GetID())
        {
            case 40: // Quest ID 40
                // eAIFactionName, Reputation Change
                GiveFactionReputation(quest, eAIFactionEast, 100);
            break;
        }
    }

    bool GiveFactionReputation(ExpansionQuest quest, typename factionType, int repChange)
    {
        factionID = eAIRegisterFaction.s_FactionIDs[factionType];
        if (factionID != 0)
        {
            //! If the quest is a group quest we add the reputation to all members unless the "RewardsForGroupOwnerOnly" is set to 1 (true).
            if (quest.GetQuestConfig().IsGroupQuest())
            {
                set<string> memberUIDs = quest.GetPlayerUIDs();
                foreach (string memberUID: memberUIDs)
                {
                    if (m_Config.RewardsForGroupOwnerOnly())
                    {
                        if (memberUID != quest.GetPlayerUID())
                            continue;
                    }

                    PlayerBase groupPlayer = PlayerBase.GetPlayerByUID(memberUID);
                    if (!groupPlayer)
                        continue;

                    groupPlayer.Expansion_AddFactionReputation(repChange, factionID);
                    return true;
                }
            }
            //! If the quest is not a group quest we just add the reputation to the main quest player.
            else
            {
                PlayerBase player = quest.GetPlayer();
                if (player)
                {
                    player.Expansion_AddFactionReputation(repChange, factionID);
                    return true;
                }
            }
        }
        return false; // FAIL
    }
};