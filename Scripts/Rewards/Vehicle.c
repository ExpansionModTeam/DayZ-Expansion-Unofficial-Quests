class CustomMission: MissionServer
{
    override void Expansion_OnQuestObjectivesComplete(ExpansionQuest quest)
    {
        super.Expansion_OnQuestObjectivesComplete(quest);

        switch (quest.GetQuestConfig().GetID())
        {
            case 40: // Quest ID 40
                // Position, Rotation, Car Classname, List of classnames for things like wheels, doors, etc
                SpawnRewardVehicle("0 0 0", "0 0 0", "MyCarName", {"MyCarPart","MyCarPart","MyCarPart"});
            break;
            case 18: // Quest ID 18
                // Position, Rotation, Car Classname, List of classnames for things like wheels, doors, etc
                SpawnRewardVehicle("0 0 0", "0 0 0", "MyCarName", {"MyCarPart","MyCarPart","MyCarPart"});
                SpawnRewardVehicle("0 0 0", "0 0 0", "MyCarName", {"MyCarPart","MyCarPart","MyCarPart"});
            break;
        }
    }

    bool SpawnRewardVehicle(vector pos, vector rot, string carName, TStringArray parts)
    {
        CarScript car;
        if (Class.CastTo(car, GetGame().CreateObject(carName, pos)))
        {
            car.SetOrientation(rot);

            foreach (string att: parts)
                car.GetInventory().CreateInInventory(att);

            car.Fill(CarFluid.FUEL, car.GetFluidCapacity(CarFluid.FUEL));
            car.Fill(CarFluid.COOLANT, car.GetFluidCapacity(CarFluid.COOLANT));
            car.Fill(CarFluid.OIL, car.GetFluidCapacity(CarFluid.OIL));

            return true;
        }
        return false; // FAILED
    }
};
