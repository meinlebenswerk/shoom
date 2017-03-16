{
    "targets": [
        {
            "target_name": "node_shoom",
            "include_dirs": [
                "vendor/shoom/include",
                "<!(node -e \"require('nan')\")"
            ],
            "sources": [ "addon.cc", "node_shoom.cc" ],
            "conditions": [
                ["OS == 'win'", {
                    "sources": [ "vendor/shoom/src/shoom_win32.cc" ]
                }],
                ["OS != 'win'", {
                    "sources": [ "vendor/shoom/src/shoom_unix_darwin.cc" ]
                }],
            ]
        }
    ]
}