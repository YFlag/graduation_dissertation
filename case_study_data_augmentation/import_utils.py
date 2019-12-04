import importlib

func_cache = None


def import_func(module_name, func_name):
    global func_cache
    # exec("global %s" % func_name)
    exec("import %s" % module_name)
    exec("importlib.reload(%s)" % module_name)
    exec("from %s import %s as func_cache" % (module_name, func_name))
    globals()[func_name] = func_cache 
    print(func_cache)
    return