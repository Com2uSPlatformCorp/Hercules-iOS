Pod::Spec.new do |spec|
  spec.name         = "Hercules"
  spec.version      = "2023.11.16"
  spec.summary      = "Hercules optional framework"
  spec.description  = "Hercules security framework provided with Hive SDK"
  spec.homepage     = "https://developers.withhive.com/"
  spec.license      = {
    :type => 'Apache-2.0', 
    :file => "#{Dir.pwd}/../../LICENSE"
  }

  spec.author       = { "Com2usPlatrformCorp" => "gamesec@com2us.com" }
  spec.platform     = :ios, "12.0"
  spec.swift_version = "5.0"

  spec.source       = { 
    :http => "https://github.com/Com2uSPlatformCorp/Hercules-iOS/releases/download/#{spec.version}/Hercules_#{spec.version}.zip"
  }

  $vendored_frameworks_path = "Hercules"
  spec.vendored_frameworks =  "#{$vendored_frameworks_path}/Hercules.xcframework"
  end
