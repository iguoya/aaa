from django.contrib import admin

# Register your models here.
from .models import GDP

class GDPAdmin(admin.ModelAdmin):

    list_display = [field.name for field in GDP._meta.fields]
    # readonly_fields = [field.name for field in GDP._meta.fields]

    list_per_page = 20
    list_filter = ['population']
    search_fields = ['city']
    # actions_on_bottom = True
    # actions_on_top = False


    actions = None
    def has_add_permission(self, request):
        return False

    def has_delete_permission(self, request, obj=None):
        return False

admin.site.register(GDP, GDPAdmin)