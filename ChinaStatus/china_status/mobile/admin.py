from django.contrib import admin

# Register your models here.
from .models import Mobile

class MobileAdmin(admin.ModelAdmin):

    list_display = [field.name for field in Mobile._meta.fields]
    # readonly_fields = [field.name for field in Mobile._meta.fields]

    list_per_page = 100
    list_filter = ['province', 'card_type']
    search_fields = ['card_type']
    # actions_on_bottom = True
    # actions_on_top = False


    actions = None
    def has_add_permission(self, request):
        return False

    def has_delete_permission(self, request, obj=None):
        return False

admin.site.register(Mobile, MobileAdmin)