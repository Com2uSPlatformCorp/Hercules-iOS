Pod::Spec.new do |s|
  s.name         = "Hercules"
  s.version      = "2024.04.03"
  s.summary      = "Hercules optional framework"
  s.description  = "Hercules security framework provided with Hive SDK"
  s.homepage     = "https://developers.withhive.com/"
  s.license      = {
    :type => 'Apache-2.0', 
    :file => "#{Dir.pwd}/../../LICENSE"
  }

  s.author       = { "Com2uSPlatformCorp" => "gamesec@com2us.com" }
  s.platform     = :ios, "12.0"

  s.source       = { 
    :http => "https://github.com/Com2uSPlatformCorp/Hercules-iOS/releases/download/#{s.version}/Hercules_#{s.version}.zip"
  }

  s.vendored_frameworks =  "Hercules.xcframework"
  s.static_framework = false

  #s.user_target_xcconfig = {
  #  "OTHER_LDFLAGS[sdk=*]": "-framework UIKit -framework WebKit -framework QuartzCore -framework CFNetwork",
  #}
end
