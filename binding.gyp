{
    "targets": [
        {
            "target_name": "capsule_videosink",
            "include_dirs": [
                "vendor/shoom/include",
                "<!(node -e \"require('nan')\")"
            ],
            "sources": [ "addon.cc", "videosink.cc" ],
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