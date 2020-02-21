from django.db import models

# Create your models here.
class Mobile(models.Model):

    section = models.IntegerField(verbose_name='手机号段', blank=True, null=True)
    province = models.CharField(verbose_name='省份', max_length=50)
    region = models.CharField(verbose_name='城市', max_length=50)
    card_type = models.CharField(verbose_name='手机卡类型', max_length=50)
    region_code = models.CharField(verbose_name='区号', max_length=50)
    post_code = models.IntegerField(verbose_name='邮编', blank=True, null=True, default='1100000')
    year = models.CharField(verbose_name='资料年份', max_length=50, default='2011年')

    def __unicode__(self):
        return self.section

    class Meta:
        verbose_name = "手机号归属地"
        verbose_name_plural = "手机号归属地"
        ordering = ['-section']