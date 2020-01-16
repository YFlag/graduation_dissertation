import importlib


""" use this if you want to debug your functions in jupyter. """
def import_(module_name, func_name=None):
    """ `import`: alternative? why exec not work? """
    module = importlib.import_module(module_name)
    importlib.reload(module)
    if func_name is None:
        return module
    else:
        func = getattr(module, func_name)
        # return func
        return module, func
 
 