import os

env = Environment ()

#prefix = "/usr/local"

prefix = ARGUMENTS.get ('prefix', "/usr/local")

# See http://www.scons.org/wiki/InstallTargets
target = os.path.join (prefix, "include")
source = "auto_enum.h"

result = SConscript (['test/SConstruct'])

# It must generate unit test before doing anything on include directory
Depends (target, result)

test_unit = Builder (action = '%s > $TARGET' % result [0])

# It must run and pass unit test before installing 
env ['BUILDERS']['RunTestUnit'] = test_unit
test_unit_result = env.RunTestUnit ('unused.output', 'SConstruct')
Depends (target, test_unit_result)

# http://www.scons.org/doc/production/HTML/scons-user/c2938.html
env.Install (target, source)
env.Alias ("install", target)

Default ('install')

auto_enum_h = os.path.join (target, source)

env.Command ("uninstall", None, [ Delete (auto_enum_h) ])
