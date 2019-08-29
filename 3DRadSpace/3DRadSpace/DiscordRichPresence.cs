﻿using System;
using DiscordRPC;

namespace _3DRadSpace
{
    public class DiscordRichPresence
    {
        RichPresence presence;
        DiscordRpcClient client;
        Timestamps time;
        public DiscordRichPresence()
        {
            presence = new RichPresence();
            presence.State = "Editing project";
            presence.Details = "New project";
            Assets assets = new Assets();
            assets.LargeImageKey = "mainicon";
            presence.Assets = assets;
            time = new Timestamps(DateTime.UtcNow);
            client = new DiscordRpcClient("612682115208708098");
            presence.Timestamps = time;
            client.SetPresence(presence);
            client.OnClose += Client_OnClose;
            client.Initialize();
        }

        private void Client_OnClose(object sender, DiscordRPC.Message.CloseMessage args)
        {
            client.ClearPresence();
            client.Deinitialize();
            client.Dispose();
        }
        public void SetPresence(string state,string detail)
        {
            presence.State = state;
            presence.Details = detail;
            time = new Timestamps(DateTime.UtcNow);
            presence.Timestamps = time;
            client.SetPresence(presence);
        }
    }
}
