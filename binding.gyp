{
    "targets": [
        {
            "target_name": "capsule_videosink",
            "sources": [ "addon.cc", "videosink.cc" ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}