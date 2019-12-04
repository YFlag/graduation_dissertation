import importlib

 
def import_(module_name, func_name=None):
    """ import: alternative? why exec not work? """
    module = importlib.import_module(module_name)
    importlib.reload(module)
    if func_name is None:
        return module
    else:
        func = getattr(module, func_name)
 
        # """ set caller's `globals()`? """
        # globals()[module_name] = module
        # globals()[func_name] = func
 
        # return func
        return module, func
 
 