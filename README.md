
sudo systemctl daemon-reload
sudo systemctl start octopus_ipc_server
sudo systemctl status octopus_ipc_server
sudo journalctl --unit octopus_ipc_server --follow
