# -*- encoding: utf-8 -*-

import json

from meta.page import Page
from meta import database

class Root(Page):
    """
    Give basic server infos
        GET /
            -> {
                "server": "server name",
                "logged_in": True/False,
            }
    """

    __pattern__ = '/'

    def GET(self):
        return self.success({
            'server': 'Meta 0.1',
            'logged_in': self.user is not None,
        })

# class Debug(Page):
#     """
#     This class is for debug purpose only
#     """
#     __pattern__ = "/debug"

#     def POST(self):
#         msg = self.data
#         if self.notifier is not None:
#             self.notifier.send_notification(msg)
#         else:
#             return self.error(error.UNKNOWN, "Notifier is not ready.")
#         return self.success({})

# XXX : Remove that cheat
class ScratchDB(Page):
    """
    Debug function to scratch db and start back to 0.
    """

    __pattern__ = "/scratchit"

    def GET(self):

        return self.success({})
